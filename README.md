# tenacitas.lib.conversions
Simple interface for type conversion

### Dependencies for the library

`tenacitas.lib.log` (only if `-DTENACITAS_LOG` is used)

`tenacitas.lib.number`

`tenacitas.lib.container`

`tenacitas.lib.async`

`tenacitas.lib.math`

### Dependencies for the tests

`tenacitas.lib.program`

`tenacitas.lib.test`


### Building

#### With your build system
The only requirement is that the path to the directory above is in the compiler include path, `-I` in `gcc`.

#### Building tests QtCreator
The file `tenacitas.lib.conversions/bld/qtcreator/tenacitas.lib.conversions.pro` contains the configuration for building the tests.


