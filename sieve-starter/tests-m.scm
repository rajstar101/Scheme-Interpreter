;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

(let ((x (seq 10 28)) (y (inf-seq 15)))
  (test-equal "basics1" 10 (car x))
  (test-equal "basics2" 11 (car ((cdr x))))
  (test-equal "basics3" 15 (car y))
  (test-equal "basics4" 16 (car ((cdr y))))
  (test-equal "basics5"  '(15 16 17 18 19 20) (first-n y 6))
  (test-equal "basics6" 22 (nth y 8)))


(test-equal "filter-mult1" '(3 5) (first-n (filter-multiples (inf-seq 2) 2) 2) )
(test-equal "filter-mult2"  '(4 5 7 8 10 11) (first-n (filter-multiples (inf-seq 3) 3) 6))
(test-equal "filter-mult3"  '(5 7 8 9 10 11 13 14 15 16 17 19) (first-n (filter-multiples (inf-seq 5) 6) 12))
(test-equal "filter-mult4"  '(5 6 8 9 10 11 12 13 15 16 17 18 19) (first-n (filter-multiples (seq 5 30) 7) 13))

(test-equal "primes3" '(2 3) (first-n (primes) 2))

