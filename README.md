# clkb
This project is nothing but my experiment with [ckb](https://github.com/mattanger/ckb-next) driver.  
It attempts to deliver simple API to control Corsair K70 RGB (Lux) keyboard leds.  
I use it for hard-coded effects and easy command-line live (like daemon) control from scripts, but it
could be used to make CLI controller instead of GUI one.

# Features
* extensive methods to provide convenient control from code
* mapping keys to 2D
* works with different frame-rates
* supports effects stack
* some pre-made effects (e.g. breathing, slowly changing colors, bitmap animations, raindrops)
* signal-interface allowing to easily bind RTMIN signals to commands
* supports Corsair K70 RGB

# Dependencies
You need K70 (can be different model if you alter key tables a little) keyboard, Linux and 
[ckb](https://github.com/mattanger/ckb-next) driver.  
It is C++14, almost C++11, but I had some more than usual fun with std::chrono here, great modern API,
if you decide to use it I hope you will like chrono as well. I think it should be fine with C++11 if time literals
are removed.  
It requires easybmp library for AnimationEffect. It is tiny lib so I included it along.

# License
MIT license