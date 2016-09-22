# Linear Regression

Linear regression is an approach for modeling the relationship between a scalar dependent variable y and one or more explanatory variables (or independent variables) denoted X. The case of one explanatory variable is called simple linear regression. For more than one explanatory variable, the process is called multiple linear regression.

## How to use

There are two binaries:
- **regLineal2D** - Basic implementation of Linear Regression for one variable
- **regLinealND** - Implementation of Multiple Linear Regression

Only execute one of them with a input file test as argument, for example:

```sh
$ ./regLinealND test/in1
```

If you need to recompile your own binaries use the **gcc compiler** and the sources in the folder **src**:
```sh
$ gcc /src/regLinealND.c -o regLinealND
```
or
```sh
$ gcc /src/regLineal2D.c -o regLineal2D
```

### Input files
The input file must have the following format:


For each row must be **p + 1** elements, **p** real numbers **x1, x2, ..., xp**, followed by one real number **d**, where **xi**, **i = 1,2,...p**, represents the values for the function **d = (w1)(xi) + (w2)(x2) + ... + (wp)(xp) + b**
and **d** is the result of the function.


#### Input files solutions

The example input files are located in the folder **test**:

**in1**

    d = 3.9545 + 2.9818X1

**in2**

    d = 5.4 + 7.5X1

**in3**

    d = 5.4 + 7.5X1 - 12.8X2 + 31.3X3

**in4**

    d = 2.5515 + 0.5827X1 + 0.3735X2 - 0.2415X3

**in5**

    d = 5.4 + 7.5X1 - 12.8X2

**in6**

    d = 5.4 + 7.5X1 - 12.8X2 + 31.3X3 - 122.45X4


## Version
1.0.0

## Author
- Oscar Esaú Peralta Rosales
- email: esau.opr@gmail.com

## References

- [Linear regression](https://en.wikipedia.org/wiki/Linear_regression)
- [Una introducción al cómputo neuronal artificial](http://www.e-libro.net/libros/libro.aspx?idlibro=7894)

## Licence

The source code is licensed under the MIT license.
