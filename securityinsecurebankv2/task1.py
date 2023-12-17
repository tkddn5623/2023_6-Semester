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
		var result = performAes256Encrypt(ivBytes, keyBytes, textBytes);
		return result;
	}
	function performAes256Encrypt(ivBytes, keyBytes, textBytes) {
        try {
            var Cipher = Java.use("javax.crypto.Cipher");
            var SecretKeySpec = Java.use("javax.crypto.spec.SecretKeySpec");
            var IvParameterSpec = Java.use("javax.crypto.spec.IvParameterSpec");

            // Make instances
            var ivSpec = IvParameterSpec.$new(ivBytes);
            var newKey = SecretKeySpec.$new(keyBytes, "AES");
            var cipherInstance = Cipher.getInstance("AES/CBC/PKCS5Padding");

			// Set context and encrypt
            cipherInstance.init(Cipher.ENCRYPT_MODE.value, newKey, ivSpec);
            var encryptedBytes = cipherInstance.doFinal(textBytes);
			
            send({"IV" : ivBytes})
            send({"KEY" : keyBytes})
            send({"BEFORE_DO_FINAL" : textBytes})
			send({"AFTER_DO_FINAL": encryptedBytes})
			
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