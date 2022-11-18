;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

(define curry-plus
    (lambda ()
        (lambda (x)
            (lambda (y)
                (+ x y)))))
                
(define curry-plus-four
    (lambda ()
        (lambda (x)
            (lambda (y)
              (lambda (z)
                  (lambda (w)
                    (+ x y z w)))))))

(test-equal "myfilter3" '() (my-filter positive? '()))


(test-equal "uncurry3" 8 ((uncurry (curry-plus)) 3 5))
(test-equal "uncurry4" 19 ((uncurry (curry-plus-four)) 1 3 5 10))

(test-equal "set3" '(1 2 3 4 5) (sort (union '(1 2 3 4 5) '(1 2 3 4 5)) <))
(test-equal "set4" '(6 7 8) (sort (union '(6 7 8) '()) <))

(test-equal "set7" '(1 2 3 4 5) (sort (intersect '(1 2 3 4 5) '(1 2 3 4 5))< ))
(test-equal "set8" '() (sort (intersect '(1 2 3 4 5) '()) <))

(test-assert "exists3-ne" (not (exists (lambda (x) (< x 3)) '())))
