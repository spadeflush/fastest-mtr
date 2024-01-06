# fastest-mtr
This page contains info for our attempt to tour all Hong Kong MTR stations in the shortest time. 

We model the MTR map as a weighted graph. Each MTR station is a vertex, while the minimum time between two stations is an edge. To implement this, we first collected the travelling times between each pair of adjacent stations. Afterwards, we took into account other modes of public transport that could potentially improve our results, such as a bus from Tsuen Wan to Tsuen Wan West or a minibus from University to Wu Kai Sha. The graph is directional and asymmetrical because travel times are direction-dependent for these modes of transport. Once we precomputed the complete graph, we ran a simulated annealing-based travelling salesman algorithm to find the fastest routes. We ultimately settled on the following:

![Proposed route](https://i.imgur.com/mpwUVSR.png)

The route is expected to take 6 hours and 39 minutes, with an unspecified amount of waiting time. The total time is expected to be not more than 8 hours.

Files:
- `dist.csv` contains the travelling times between pairs of stations (coded as numbers) in the format of `{mode of transport, starting station, ending station, time}`;
- `stationcode.csv` contains the list of stations and their corresponding numbers;
- `simulatedAnnealing.cpp` contains a messy but working code returning possible routes and their corresponding times.
