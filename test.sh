#! /bin/sh
bundle config --local path vendor/bundle
bundle exec arduino_ci_remote.rb  --skip-compilation

# Other testing cd Ethernet; bundle exec arduino_ci.rb  --skip-examples-compilation
