Appoxee SDK - US
===========
This repository contains the Appoxee iOS SDK.

Integration
-----------

*Cocoa pods

```ruby
target 'project_name' do
    pod 'AppoxeeSDK'
end
```

*OR*


```ruby
target 'project_name' do
    pod 'AppoxeeSDK', :git => 'https://github.com/AppoxeeMobile/iosArtifacts.git', :tag => '4.0.11'
end
```

*Manual

Drag and drop the .framework to your project.


Configuration file
------------------

Make sure to provide an ```AppoxeeConfiguration.plist``` file.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>sdk</key>
    <dict>
        <key>dmc_system_id</key>
        <integer>11111111</integer>
        <key>sdk_key</key>
        <string>222222222.2222</string>
    </dict>
</dict>
</plist>
```

License
-------
http://www.appoxee.com/terms/

