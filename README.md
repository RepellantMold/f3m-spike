# F3M Spike
Fast S3M play routine for whatever, that also happens to work on the Game Boy Advance (forked)

Made in 2015 by GreaseMonkey under Public Domain.
Forked by RepellantMold in 2023 under BSD Zero clause.

Test module is "Point of Departure" by Necros (pod.s3m), which you can get here (as it is not Public Domain I've decided to post a link to it instead): http://lite.modarchive.org/module.php?55696

(While nintendo.bin is also not PD, it's a requirement in order to make this actually run on a GBA, and it's pretty small so it's included)

## Compiling

### Compiling the GBA version

You will need gcc and binutils for ARMv4T or higher.

> **Note**
> GreaseMonkey personally uses gcc-arm-none-eabi 4.8 2014q1 that is *somewhere* in FreeBSD's ports repository (try devel/gcc-arm-embedded).

For Windows, you can run gba_build.bat

For other OSes, run `./gba_build.sh` in a terminal, it will spit out a file called `gba_f3m.gba`.

Use that in your favourite emulator, or try it out on actual hardware!

> **Note**
> This will probably not work immediately, so you will have to edit `gba_build.sh` and make it use the right prefix for your ARM cross compiler.
> (When building on a Raspberry Pi, you would leave this blank.)

#### Changing the default module

- modify `boot.S`, do a different `.incbin` after `s3m_beg`
- recompile

it should work just nicely.

### Compiling the Open Sound System version

You will need a C compiler that can be accessed by running `cc`.

Run `./oss_build.sh` in a terminal.

This doesn't work on Windows.
It's a rather simple player example, and you can learn from it and adapt it to work for you.

## TOLISTS

### TODO

* Allow playback of oneshot samples by the audio engine
* DevKitARM/DevKitPRO support

### TODON'T

* Interpolation
  - It'd likely take up too much CPU time.
* Quirks/additions from other trackers
  - ST 3.21 is the main target of accuracy here.
* Adlib channel support
  - It's too unpopular and it's ditto for CPU time.

#### Optimization related (GBA only)
- Using a shift instead of a multiply for volume calculation
  - there wasn't any noticeable speed gain, while the audio sure sounded awful!
- Using a volume lookup table
  - code compiles to an MLA instruction without it, which is faster than doing LDRH then ADD
- Precaching more than one sample ahead
  - despite the fact that gamepak reads are kinda slow, this isn't the bottleneck!
- While it's possible to copy the module into fast RAM, it doesn't really improve things. It *is* supported, though it's commented out.

### TOMIGHTDO

* Proper stereo support, not interested in getting this working on a GBA.
  - This would require us to do 16 bytes per sample which is slow!
* Big-endian support.

### TOYOUDOIT

* Minimal players for other audio frameworks.

