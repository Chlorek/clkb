# clkb
This project is nothing but my experiment with [ckb](https://github.com/mattanger/ckb-next) driver.  
It attempts to deliver simple API to control Corsair K70 Lux RGB keyboard leds. It supports different framerate
and simple effects (breathing, slowly changing colors, animation with series of bitmaps).  

# Dependencies
You need K70 (can be different model if you alter key tables a little) keyboard, Linux and 
[ckb](https://github.com/mattanger/ckb-next) driver.  
It is C++14, almost C++11, but I had some more than usual fun with std::chrono here, great modern API,
if you decide to use it I hope you will like chrono as well. I think it should be fine with C++11 if time literals
are removed.  
It requires easybmp library for AnimationEffect. It is tiny lib so I included it along.