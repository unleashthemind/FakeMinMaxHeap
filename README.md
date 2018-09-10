# FakeMinMaxHeap
this is based off of https://userpages.umbc.edu/~park/cs341.s18/projects/proj4.shtml
with a major difference in how I chose to implement the solution, which I think is more elegant.

Driver.cpp was given and not written by me.

Rather than have each heap keep track of the other heap in order to achieve O(log(n)), I'm achieving O(log(n)) by
utilitizing the property of heaps that the smallest value of a maxHeap will always be in the leaves and vice-versa
so if you search your heap array backwards you can achieve O(log(n)) anyways.
