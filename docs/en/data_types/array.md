# Array(T) {#data-type-array}

An array of `T`-type items. `T` can be any data type, including an array.

## Creating an array {#creating-an-array}

You can use a function to create an array:

``` sql
array(T)
```

You can also use square brackets.

``` sql
[]
```

Example of creating an array:

``` sql
SELECT array(1, 2) AS x, toTypeName(x)
```

``` text
┌─x─────┬─toTypeName(array(1, 2))─┐
│ [1,2] │ Array(UInt8)            │
└───────┴─────────────────────────┘
```

``` sql
SELECT [1, 2] AS x, toTypeName(x)
```

``` text
┌─x─────┬─toTypeName([1, 2])─┐
│ [1,2] │ Array(UInt8)       │
└───────┴────────────────────┘
```

## Working with Data Types {#working-with-data-types}

When creating an array on the fly, ClickHouse automatically defines the argument type as the narrowest data type that can store all the listed arguments. If there are any [Nullable](nullable.md#data_type-nullable) or literal [NULL](../query_language/syntax.md#null-literal) values, the type of an array element also becomes [Nullable](nullable.md).

If ClickHouse couldn’t determine the data type, it generates an exception. For instance, this happens when trying to create an array with strings and numbers simultaneously (`SELECT array(1, 'a')`).

Examples of automatic data type detection:

``` sql
SELECT array(1, 2, NULL) AS x, toTypeName(x)
```

``` text
┌─x──────────┬─toTypeName(array(1, 2, NULL))─┐
│ [1,2,NULL] │ Array(Nullable(UInt8))        │
└────────────┴───────────────────────────────┘
```

If you try to create an array of incompatible data types, ClickHouse throws an exception:

``` sql
SELECT array(1, 'a')
```

``` text
Received exception from server (version 1.1.54388):
Code: 386. DB::Exception: Received from localhost:9000, 127.0.0.1. DB::Exception: There is no supertype for types UInt8, String because some of them are String/FixedString and some of them are not.
```

[Original article](https://clickhouse.tech/docs/en/data_types/array/) <!--hide-->
