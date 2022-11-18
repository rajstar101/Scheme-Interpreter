;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

(test-equal "neg-inf-seq1" -3 (car (inf-seq -3)))
(test-equal "neg-inf-seq2" -2 (car ((cdr (inf-seq -3)))))
(test-equal "first-n-edge1" '(3 4) (first-n (seq 3 4) 20))
(test-equal "first-n-edge2" '() (first-n (seq 3 2) 20))

(test-assert "nth-edgh1" (not (nth (seq 3 2) 5)))
(test-assert "nth-edge2" (not (nth (seq 3 5) 25)))

(test-equal "filter-mult-first-n-edge"  '(5 6 8 9 10 11 12 13 15 16 17 18 19 20 22 23 24 25 26 27 29 30) (first-n (filter-multiples (seq 5 30) 7) 500))



(test-equal "primes1" '(2 3 5 7 11 13 17 19 23 29) (first-n (primes) 10))
(test-equal "primes2" 71 (nth (primes) 20))
