| program     | sleep | reader proc | writer proc | user time | kernel time | output sample  		  |
| spinlock    | no    | 100	    | 100	  | 19,965s   | 0,001s 	    | 7180198 15222164 -8041966   |
| mutex	      | no    | 100	    | 100	  | 12,391s   | 7,572s      | 5311064 10385544 -5074480   |
| conditional | no    | 100  	    | 100         | 11,713s   | 7,486s      | 6068080 6068001 79          |
| semaphore   | no    | 100  	    | 100         | 8,962s    | 9,891s      | 2809212 2809211 1           |
| spinlock    | yes   | 100 	    | 8           | 11,343s   | 0,040s      | 805600 124045774 -123240174 |
| mutex       | yes   | 100 	    | 25	  | 10,133s   | 1,685s      | 763015 88420249 -87657234   |
| conditional | yes   | 3 	    | 5           | 1,080s    | 0,360s      | 856412 856401 11            |
| semaphore   | yes   | 25 	    | 35	  | 2,162s    | 2,308s      | 690650 690650 0             |

