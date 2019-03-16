//
// Created by Josh Martin on 2019-03-16.
//

#ifndef H4_GENERAL_H
#define H4_GENERAL_H

#define NUMBER_OF_CUSTOMERS 5 // `n`
#define NUMBER_OF_RESOURCES 3 // `m`

#define TRUE 1
#define FALSE 0

/* # BANKER'S Algorthim
 *
 * For this projet, you will write a multithreaded program that implements
 * the banker's algorithm discussed in Section 7.5.3. Several customers request
 * and release resources from the bank. The banker will grant a request only
 * if it leaves the system in a safe state. A request that leaves the system in
 * an unsafe state will be deniced. The programming assignment combines
 * three separate topics:
 *  1) Multithreading
 *  2) preventing race conditions
 *  3) deadlock Avoidance
 *
 * ## The Banker
 * The banker consider requests from `n` customers from
 * `m` resources types (section 7.5.3). The banker will keep track of the
 * resource using the following data structures.
 *
//-----------------------------------------------------------------------------
*/
/* In this project you will implement the Banker’s problem described in Chapter
   7 of your book (p345/346). Use the Pthreads library and the VM that you built
   in HMW 1 to complete this project. */

/*You may assume that you have three resources with the following number of
  instances (available array) The number of customers, n, can vary.  Initialize
  your maximum array with random numbers less than available array Every time
  you make an allocation show the following:
 * The request
 * Allocation
 * Available
 * Maximum
 * Need
 Indicate whether the request was successful or denied In your report show an
 example of a denied request and a granted request and explain the results.
 Why was the request denied or granted. */

#endif //H4_GENERAL_H
