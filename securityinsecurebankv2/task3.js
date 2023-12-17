Java.perform(function() {
    var targetClassName = "com.android.insecurebankv2.ChangePassword";
    var targetFieldName = "PASSWORD_PATTERN";
    
    var targetClass = Java.use(targetClassName);
    
    // Hook the class initialization
    targetClass.$init.implementation = function() {
        // Call the original initialization
        this.$init.apply(this, arguments);

        try {
            // Use reflection to get the field
            var field = targetClass.class.getDeclaredField(targetFieldName);
            field.setAccessible(true);

            // Log the original value
            var originalValue = field.get(null);
            console.log("[Frida] Original value of " + targetFieldName + ": " + originalValue);

            // Modify the final modifier
            var modifiersField = java.lang.reflect.Field.class.getDeclaredField("modifiers");
            modifiersField.setAccessible(true);
            modifiersField.setInt(field, field.getModifiers() & ~java.lang.reflect.Modifier.FINAL);

            // Change the value of the private static final string
            field.set(null, "((?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%]).{10,20})");

            // Log the modified value
            var modifiedValue = field.get(null);
            console.log("[Frida] Modified value of " + targetFieldName + ": " + modifiedValue);

            console.log("[Frida] Value of " + targetFieldName + " changed successfully!");
        } catch (e) {
            console.error("[Frida] Error in changing " + targetFieldName + ":", e);
        }
    };
});