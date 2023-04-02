# tenacitas.lib.conversions
Simple interface for type conversion

## Testing
In order to compile the tests, it is necessary to clone the `tenacitas.lib.test` and `tenacitas.lib.program` repositories aside `tenacitas.lib.conversions`, like this:

    .
    ├── home
            ├── user
                ├── development
                    ├── tenacitas.lib.conversions
                    ├── tenacitas.lib.program
                    ├── tenacitas.lib.test

## Default building system

There is a respository with build system based on QtCreator in `tenacitas.bld`, which should be also cloned aside `tenacitas.lib.conversions`, like this:

    .
    ├── home
            ├── user
                ├── development
                    ├── tenacitas.bld            
                    ├── tenacitas.lib.conversions
                    ├── tenacitas.lib.program
                    ├── tenacitas.lib.test


## Using your own building system

If you want to use another build system, you will need to add the path to the directory above all these directories, in the example `/home/user/development` to the include path of the compiler you are using. 
In `gcc` that would be `-I=/home/user/development`.

