# Live From Death – Stupid Gopher server

Web is cursed. Gopher is simple, easy to use and easy to develop for. As I needed a server to host my own files, developing one was a good way to learn about the protocol. The software works as follow: add your Gopher files (raw files, with commands) to the `space/` folder and run the server.

Indexing of the space is done once at startup, so restarting is needed to take changes into account. This is done so that files can be cached very easily. Meanwhile, the server is mono-threaded, so do not expect too much efficiency, even though it works well. Do not expect too many people to visit your files anyway.

The source code is meant to be compiled on a Linux machine, using `gcc`. Nothing special needs to be done: use GCC with some tweaks as you want.