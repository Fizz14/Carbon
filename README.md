# Carbon
This was a codebase I built as a teenager in highschool. Over the years, I added mesh loading/rendering, Tetris, homemade sorting algorithms, and a showcase of emergent behavior. Runs on SDL, so it draws every pixel, because I wanted to practice with low-level code.

carbon-renderer is a branch I'm very proud of. It contains mesh loading with a custom filetype, wireframe/color/flat-shading, and some simple viewing options. Everything
is done by the software (no hardware acceleration) because I wanted to practice with low-level code, but this also meant that gourand shading (partially implemented)
was too computationally expensive to run well, so that's where I stopped.

But if you are looking for a c++ implementation of vertex transformation formula without external libraries, this might be the most helpful source code on the internet.

To build, you must correctly link SDL2.
