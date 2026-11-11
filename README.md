# NSFNET Topology Simulator for Elastic Optical Networks (OPNET)

> Part of my MSc thesis, *Optimization of Fragmented Spectrum in Elastic Optical Networks Using Pattern Recognition* (University of Qom, 2022; supervisor: Dr Mohsen Nickray).

A simulation model of the **NSFNET** backbone topology built in **OPNET Modeler** for studying traffic and spectrum allocation in **elastic optical networks (EONs)**. Custom node, packet and process models generate a stream of connection requests between the 14 network nodes and log every request for later analysis.

![NSFNET topology](Network%20Topology/NSFNET.png)

## Traffic model

The generator process (`Process/malayeriprocess1`) creates connection requests with:

| Parameter | Model |
|---|---|
| Arrivals | Poisson process (exponentially distributed inter-arrival times) |
| Source / destination | Uniformly chosen among nodes 0–13 |
| Requested bandwidth | Uniform integer number of frequency slots (FS) |
| Holding time | Exponentially distributed (mean 20 time units) |
| Recurring traffic | A periodic request stream (node 1 → node 10, 5 FS) is injected so that repeating patterns exist in the traffic |

Each request is sent as an `EONPK` packet with the fields `id`, `src`, `dest`, `need` (FS), `holding_time`, `endtime` and `type` (0 = random, 1 = periodic).

## Output

Every request is appended to a trace file, one line per request:

```text
SIMTIME: 0.000908   source:11 and Dest:4 and needed:8 and holding time:69.347106
```

| Field | Meaning |
|---|---|
| `SIMTIME` | Arrival time of the request |
| `source` | Source node |
| `Dest` | Destination node |
| `needed` | Requested number of frequency slots |
| `holding time` | How long the connection stays up before its resources are released |

A sample trace with about 100,000 requests is included in [`Result/cons22.txt`](Result/cons22.txt).

## Repository structure

```text
Network Topology/NSFNET.png   Topology used in the simulation
Process/                      OPNET process, node and packet models
  malayeriprocess1.pr.*       Traffic generator (random + periodic requests)
  malayeryprocess2.pr.*       Node process
  myeonnode.nd.m              EON node model
  EONPK.pk.m, eonpacket.pk.m  Packet formats
Result/cons22.txt             Sample output trace
```

## How to run

1. Copy the files in `Process/` into your OPNET Modeler model directory.
2. Build the NSFNET network from `myeonnode` nodes as in the topology figure.
3. Update the output path in `malayeriprocess1` (currently `E:/malayeri/cons22.txt`).
4. Compile the process models and run the simulation; the trace file is written as the simulation runs.

## Related repositories

| Step | Repository |
|---|---|
| 1. Generate traffic in OPNET | [NSFNET Topology Simulator for EONs](https://github.com/malayerimahdi/NSFNET-Network-Topology-Simulator-on-Opnet-For-Elastic-Optical-Network-EON-) |
| 2. Find recurring traffic patterns | [EON Simulator: Real-time Packet Pattern Finder](https://github.com/malayerimahdi/EON-Simulator-Real-time-Packet-Pattern-Finder-) |
| 3. Explore ML-based slot allocation | [AI-Based Dynamic Resource Allocation](https://github.com/malayerimahdi/AI-Based-Dynamic-Resource-Allocation-for-Reducing-Blocking-Probability) |

## Author

**Mohammad Mahdi Malayeri** · [Website](https://malayerimahdi.github.io/) · [LinkedIn](https://www.linkedin.com/in/malayerimahdi/) · malayerimahdi@gmail.com

<!-- Previous README (kept for reference):
# NSFNET-Network-Topology-Simulator-on-Opnet-For-Elastic-Optical-Network-EON-
NSFNET Network Topology Simulator on Opnet For Elastic Optical Network (EON)

The first area of ​​the request arrival time

The second line of origin

The third destination point

The fourth requested number of FS

And the fifth is the connection maintenance time, which means that after that time, the connection will be terminated and its resources will be released.
-->
