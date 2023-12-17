#!python 2.7.18
import frida, sys

def on_message(message, data):
	print(message)


PACKAGE_NAME = "com.android.insecurebankv2"

jsscript = """
send("[FRIDA]-----Start Script-----");

Java.perform(function() {
	send("[FRIDA]-----Java.perform-----");
	var className = Java.use("com.android.insecurebankv2.CryptoClass");
	className.aes256encrypt.implementation = function(ivBytes, keyBytes, textBytes) {
		send(this.aes256encrypt(ivBytes, keyBytes, textBytes));
		var result = performAes256Encrypt(ivBytes, keyBytes, textBytes);
		return this.aes256encrypt(ivBytes, keyBytes, textBytes);
	}
    // Manually implement the AES encryption logic
    function performAes256Encrypt(ivBytes, keyBytes, textBytes) {
        try {
            var cipher = Java.use("javax.crypto.Cipher");
            var secretKeySpec = Java.use("javax.crypto.spec.SecretKeySpec");
            var ivParameterSpec = Java.use("javax.crypto.spec.IvParameterSpec");

            // Convert byte arrays to Java objects
            var ivSpec = Java.cast(ivParameterSpec.$new(ivBytes), ivParameterSpec);
            var newKey = Java.cast(secretKeySpec.$new(keyBytes, "AES"), secretKeySpec);

            // Create Cipher instance
            var cipherInstance = cipher.getInstance("AES/CBC/PKCS5Padding");

            // Initialize Cipher
            cipherInstance.init(1, newKey, ivSpec); // 1 corresponds to Cipher.ENCRYPT_MODE

            // Perform encryption
            var encryptedBytes = cipherInstance.doFinal(textBytes);

            return encryptedBytes;
        } catch (e) {
            console.error("[FRIDA] Error in performAes256Encrypt:", e);
            return null;
        }
    }
});
"""

process = frida.get_usb_device(1).attach(PACKAGE_NAME)
script = process.create_script(jsscript)
script.on('message', on_message)
print("[FRIDA]-----Running Hook-----")
script.load()
sys.stdin.read()