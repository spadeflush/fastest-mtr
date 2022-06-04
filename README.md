# fastest-mtr
This pages contains info for our attempt to tour all Hong Kong MTR stations in the shortest time. 

In our model, the MTR map is modelled as a weighted graph. Each vertex represents an MTR station, while each edge represents the minimum time between the pair of stations. To implement this, the travelling times between each pair of adjacent stations was first collected. Afterwards, other modes of public transport which would greatly improve our result were considered, such as buses from Tsuen Wan to Tsuen Wan West or a minibus from University to Wu Kai Sha. The graph is directional and asymmetrical due to the unequal times when travelling in either direction for these modes of transport. Finally, with a complete graph precomputed, a simulated annealing-based travelling salesman algorithm was run. The fastest few routes were considered, and we ultimately settled on the following:

![Proposed route](https://i.imgur.com/mpwUVSR.png)

The route is expected to take 6 hours and 39 minutes, with an unspecified amount of waiting time. The total time is expected to be not more than 8 hours.

Files:
- `dist.csv` contains the travelling times between pairs of stations (coded as numbers) in the format of `{mode of transport, starting station, ending station, time}`;
- `stationcode.csv` contains the list of stations and their corresponding numbers;
- `simulatedAnnealing.cpp` contains a messy but working code returning possible routes and their corresponding times.
