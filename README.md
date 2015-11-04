# wed
Wil's editor

![wed](https://cloud.githubusercontent.com/assets/8480417/10098414/0b5902ee-6379-11e5-9c3d-29a1c5acc428.png)

## What I want out of a text editor
- client / daemon architecture
- asynchronous daemon
- piece-chain text manipulation
- api open to all of unix land
- all of unix land available within editor (exec[vp])
- structural regexp
- multifile support
- support for plumber-like utility

## Other things maybe:
- use X11 clipboard for cut n paste
- multi-window (for the system to use, not for user to split screens)

Basically I want sam but without the mouse (and a terminal interface instead)

## research excursions

- [piece chains](https://github.com/filwisher/pisschin)
- [client/daemon architecture](https://github.com/filwisher/lurker)

## implementation
- client/server communication with named pipes (see [issue #8](https://github.com/FilWisher/wed/issues/8))
- text management with piece chains
- ... ?

## roadmap
- load and save text
- receive basic edit commands from mock client ("./send-command 'raw commandstring'")

## sources
[0] [Data Structures for Text Sequences](https://www.cs.unm.edu/~crowley/papers/sds.pdf)

[1] [Project Oberon](https://www.inf.ethz.ch/personal/wirth/ProjectOberon/PO.System.pdf)

[2] [sam](http://doc.cat-v.org/plan_9/4th_edition/papers/sam/)
