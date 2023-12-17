#!python 2.7.18
#p3 failed. this code incorrect
import frida, sys

def on_message(message, data):
    print(message)

PACKAGE_NAME = "com.android.insecurebankv2"

jsscript = """
send("[FRIDA]-----Start Script-----");

Java.perform(function() {
	send("[FRIDA]-----Java.perform-----");
    var className = "com.android.insecurebankv2.ChangePassword";
    var methodName = "onCreate";
    var fieldName = "PASSWORD_PATTERN";

    var targetClass = Java.use(className);
    var targetMethod = targetClass[methodName];

    targetMethod.implementation = function(a) {
        console.log("........")
        try {
            // Change the value of the private static final string
            var fieldValue = "((?=.*\\d)(?=.*[a-z])(?=.*[@#$%]).{10,20})";
            var field = targetClass.class.getDeclaredField(fieldName);
            field.setAccessible(true);
            console.log("[Frida] Original value of " + fieldName + ": " + field.get(null));
            field.set(null, fieldValue);
            console.log("[Frida] Value of " + fieldName + " changed successfully!");
            console.log("[Frida] Modified value of " + fieldName + ": " + field.get(null));
        } catch (e) {
            console.error("[Frida] Error in changing " + fieldName + ":", e);
        }
        return this.onCreate(a);
    };
});
"""

process = frida.get_usb_device(1).attach(PACKAGE_NAME)
script = process.create_script(jsscript)
script.on('message', on_message)
print("[FRIDA]-----Running Hook-----")
script.load()
sys.stdin.read()