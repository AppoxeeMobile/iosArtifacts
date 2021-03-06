Pod::Spec.new do |s|

  s.name         = "AppoxeeSDK"
  s.version      = "4.1.4"
  s.summary      = "Appoxee SDK enables developers to harnest the full power of Appoxee on their iOS applications."
  s.description  = 	<<-DESC
  					Appoxee SDK enables push notification in your iOS application, for engaging your application users and increasing retention.
                   	DESC
  s.homepage     = "http://www.appoxee.com"
  s.license      = { :type => "Custom", :file => "AppoxeeLicence.txt" }
  s.author       = { "Appoxee" => "info@appoxee.com" }
  s.source       = { :git => "https://github.com/AppoxeeMobile/iosArtifacts.git", :tag => "4.1.4" }
  s.ios.framework = 'UserNotifications'
  s.platform     = :ios, "8.0"
  s.ios.vendored_frameworks = "SDK/AppoxeeSDK.framework"
  s.preserve_paths = 'SDK/AppoxeeSDK.framework'
  s.resource_bundle = { 'AppoxeeSDKResources' => 'SDK/AppoxeeSDKResources.bundle' }
  s.requires_arc = true

end
