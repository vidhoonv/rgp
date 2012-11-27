====================================
ROUTE GUIDANCE PROTOCOL [VANETS]
====================================

INTRODUCTION
============

In today’s world, the number of vehicles on road is increasing at a rapid
rate contributing to an increase in congestion on the road. This has necessitated the need for a system to assist the drivers during travel. Many solutions do exist for this aspect but have certain short-comings. They are either very expensive (in the case of infrastructure based solutions) or not accurate (in case of
decentralized solutions operating based on historic data).

In an attempt to alleviate these issues, we present a decentralized solution
for route guidance which takes into account the dynamic nature of traffic and
operates based on real-time traffic information rather than historic data. The
motivation for this endeavor lies in the following assumptions and inferences:
although patterns in traffic can be obtained for a road, on a given day there will be many deviations from the expected pattern and hence using the real-time
traffic information is much more accurate than using pre-computed data.

SCOPE
=====

The aim of this project is to automatically guide a driver of a vehicle to
travel from one place to another in a city through a decentralized solution with
no infrastructure requirements. The system makes use of the current state of
traffic on the roads by enabling communication between vehicles. The traffic
information is obtained dynamically and the system will guide the driver in a
route based on his preferences. The goal of the system is to:

• Provide an effective communication mechanism between vehicles

• Compute a path which takes into account both the distance as well as the
time

• Take into account the movement/change in traffic during the journey of
a vehicle by recalculating the efficient path before approaching every
junction

• Minimize packets sent in the network by making vehicles respond only to
vehicles for which they have relevant information.

CONRIBUTIONS
============

The contributions of this project are threefold. First, it creates a real time
test bed for evaluating any route guidance mechanism. Second, it evaluates the
performance of weight based cost function on real time traffic scenarios. Third,
based on the findings from evaluation, it identifies the open issues and possible ways to address them.
