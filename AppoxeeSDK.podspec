Pod::Spec.new do |s|

  s.name         = "AppoxeeSDK"
  s.version      = "4.0.10"
  s.summary      = "Appoxee SDK enables developers the harnest to full power of Appoxee on their iOS applications."
  s.description  = 	<<-DESC
  					Appoxee SDK enables push notification in your iOS application, for engaging your application users and increasing retention.
                   	DESC
  s.homepage     = "http://www.appoxee.com"
  s.license      = { :type => "Custom", :file => "AppoxeeLicence.txt" }
  s.author       = { "Appoxee" => "info@appoxee.com" }
  s.source       = { :git => "https://github.com/AppoxeeMobile/iosArtifacts.git", :tag => "4.0.10" }
  s.platform     = :ios, "7.0"
  s.ios.vendored_frameworks = "SDK/AppoxeeSDK.framework"
  s.preserve_paths = 'SDK/AppoxeeSDK.framework'
  s.requires_arc = true

end
