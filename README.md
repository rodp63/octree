# Octree
To run the project:
1. Select the directory of the tree
```bash
$ cd PR-octree
```
or
```bash
$ cd range-octree
```
2. Run the following commands:
```bash
$ cmake -B build
$ cd build
$ make
$ ./octreein
```
The example obj file is in _'files/sample.obj'_, but another obj file can be loaded specifying the file path as a parameter in the executable:
```bash
$ ./octree obj_path
```
