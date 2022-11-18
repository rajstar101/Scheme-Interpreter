;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

(test-equal "curry1" 30 ((((curry3 *) 2) 3) 5))
(test-equal "uncurry1" 30 ((uncurry3 (curry3 *)) 2 3 5))
(test-equal "uncurry2" '(9 8 7) ((uncurry3 (curry3 list)) 9 8 7))

(test-equal "myfilter1" '(1 3 4) (my-filter positive? '(1 -2 3 4 -5)))
(test-equal "myfilter2" '() (my-filter positive? '(-1 -2 -3 -4 -5)))

(test-equal "set1" '(1 2 3 4 5 6 7) (sort (union '(1 2 3) '(4 5 6 7)) <))
(test-equal "set2" '(1 2 3 4 6) (sort (union '(1 2 3) '(4 3 6 2)) <))

(test-equal "set5" '() (intersect '(1 2 3) '(4 5 6 7)))
(test-equal "set6" '(2 3) (sort (intersect '(1 2 3) '(4 3 6 2)) <))

(test-equal "exists1" #t (exists (lambda (x) (< x 3)) '(9 2 1 8 7)))
(test-equal "exists2" #t (not (exists (lambda (x) (< x -5)) '(-1 0 1))))
