# Social-Network-cli

This project provides a lightweight C implementation of a social network user relationship system. It utilizes linked lists to manage bidirectional "follow" and "follower" connections, allowing users to efficiently connect and disconnect from one another while maintaining individual user profile data.

While the data is stored using lists, the system conceptually functions as a **Directed Graph**. In this structure, each user acts as a **node (vertex)**, and every "follow" relationship represents a **directed edge** from one user to another, enabling you to model complex social interactions and network topologies.

- How to use it?

```bash
gcc social_network.c -o sn
./sn
```