# Go-Back-N-ARQ
A C++ program to implement Go Back N ARQ in noisy channel. 
The sender should send more than one data frames(within window size) and start a timer for it. 
If it receives acknowledgment, then it should move its sending window, reset timer to the first outstanding frame and send next set of frame/frames. If it does not receive acknowledgment before the timer times out, it should retransmit all the outstanding frames. (i.e frames which have not yet received acknowledgment). The receiver should send acknowledgment only if it receives the expected frame successfully. It should discard all other packets which are out of order.
