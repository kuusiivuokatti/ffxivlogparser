1. [Structure](doc/log.md#structure)
2. [Reading](doc/log.md#reading)
3. [Issues](doc/log.md#issues)

---

#### Structure

Each log consists of three parts:
1. Header information, which tells the file and content lengths
2. Message information, which tells us the offsets of each message
3. Messages, which contain the timestamp, type and message

---

#### Reading

Each of the messages can be read separately, since we know the size needed to be read from parts 1 and 2 of the file structure. This leaves us with getting out the actual content of the message, where the only variable of varying size is the message content. Message content length can be calculated since we know the starting location and the end of each offset.

---

#### Issues

The log message information seems to be static in size, however the logs can contain messages outside the known range. Need to look into this more, but it is possible that some messages will be missing with this logic, since they are not included in the original message offset information.
