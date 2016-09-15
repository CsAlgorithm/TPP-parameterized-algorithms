# TPP-parameterized-algorithms

This repository contains the source code and the data set of experiments of our parameterized algorithms introduced in [Parameterized algorithms for the traveling purchaser problem with additional constraints].

###Environment
Algorithms are implemented in C++, compiled and tested on a Ubuntu Linux PC with an Intel Core i7 2.3GHz CPU and a 8GB RAM.


###DATA SET

The file "data.rar" is the data set that we have been tested, the file format of each instance in the data set is the same as the file format in benchmark generated by [A branch-and-cut algorithm for the undirected traveling purchaser problem. Laporte G., Riera-Ledesma J.]. The benchmark of Laporte can be found online: http://webpages.ull.es/users/jriera/TPP.htm. The instances in the benchmark introduced above is not abundant enough, since it does not contain the instance suitable for testing the parameterized algorithms.

The method that we used to generate our instance is similar to the method introduced in Laporte's article. We first use the TSPLIB to get the positional information, and then we randomly assign each product to a random number of markets. For a single product, its price is different in different markets, so we first randomly generate a prime price for each product, and the price of it in different market randomly fluctuates within 15% based on prime price.


###TPP-B

We compared our parameterized algorithm of TPP-B with the most recent results introduced in [The traveling purchaser problem with budget constraint. Renata Mansini, Barbara Tocchella]. The Renata's article mainly introduced two heuristic algorithm based on local search. We can not get access to the original source code of their experiment, so we reimplemented the more competitive algorithm MVNS in C++.

The source code of our experiment of TPP with budget constraint is in the folder /TPP_B.

Arguments: FileName M K B

FileName: The file name of the instance file.</br>
M:The number of markets.</br>
K:The number of products.</br>
B:A minimum budget multiplier.</br>

###TPP-S2

We compared our parameterized algorithm of TPP-S2 with the most recent results introduced in [Models for a traveling purchaser problem with additional side-constraints. Luis Gouveia, Ana Paias]. This article introduced two relaxation algorithm, the first is Lagrangian relaxation and the second is dynamic programming relaxation. Because our algorithm is based on dynamic programming, so we compare our algorithm with the latter. Also we can not get access to the original source code of their experiment, so we reimplemented their algorithm in C++.

The source code of our experiment of TPP-S2 is in the folder /TPP_S2.

Arguments: FileName M K U Q

FileName: The file name of the instance file.</br>
M:The number of markets.</br>
K:The number of products.</br>
U:At most U products can be bought from a supplier.</br>
Q:At most Q markets can be visited.</br>

###TPP-S1

We compared our parameterized algorithm of TPP-S1 with the algorithm introduced in [Models for a traveling purchaser problem with additional side-constraints. Luis Gouveia, Ana Paias]. The original algorithm in this article is designed for TPP-S2, we can modify it to fit the TPP-S1 just by setting the parameter D to infinity. Note that parameter D controls a limit on the number of items bought per market.

The source code of our experiment of TPP-S2 is in the folder /TPP_S1.

Arguments: FileName M K Q

FileName: The file name of the instance file.</br>
M:The number of markets.</br>
K:The number of products.</br>
Q:At most Q markets can be visited.</br>
