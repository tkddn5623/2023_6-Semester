#!python 2.7.18
import frida, sys

def on_message(message, data):
    print(message)

PACKAGE_NAME = "com.android.insecurebankv2"

jsscript = """
send("[FRIDA]-----Start Script-----");

Java.perform(function() {
	send("[FRIDA]-----Java.perform-----");
    var className = "com.android.insecurebankv2.LoginActivity";
    var methodName = "onCreate";

    var targetClass = Java.use(className);
    var targetMethod = targetClass[methodName];

    targetMethod.implementation = function() {
        var result = this[methodName].apply(this, arguments);
        try {
            var viewId = Java.use("com.android.insecurebankv2.R$id");
            send(viewId.button_CreateUser);
            var viewClass = Java.use("android.view.View")
            var view = this.findViewById(viewId.button_CreateUser.value);
            var View = Java.use("android.view.View");

            var setVisibilityMethod = View.setVisibility.overload('int');
            // Set visibility
            setVisibilityMethod.call(view, 0);

            console.log("[FRIDA]-----SetVisibility hooked successfully!-----");
        } catch (e) {
            console.error("[FRIDA]-----Error in setVisibility hook:", e);
        }
        return result;
    };
});
"""

process = frida.get_usb_device(1).attach(PACKAGE_NAME)
script = process.create_script(jsscript)
script.on('message', on_message)
print("[FRIDA]-----Running Hook-----")
script.load()
sys.stdin.read()