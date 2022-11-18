;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

(test-equal "gen-list-single" '(3) (gen-list 3 3))
(test-equal "gen-list-empty" '() (gen-list 5 3))

(define one-lazy-item (gen-lazy-list 3 3))
(test-equal "gen-lazy-list-single" 3 (car one-lazy-item))
(test-assert "gen-lazy-list-single-end-no-error" (not ((cdr one-lazy-item))))

(test-assert "gen-lazy-list-empty-no-error" (not (gen-lazy-list 5 3)))

(test-assert "make-lazy-list-empty-no-error" (not (make-lazy '())))
(test-assert "make-lazy-end-no-error" (not ((cdr ((cdr ((cdr (make-lazy '(3 4 5))))))))))



;; Test pair-sum? edge cases
(test-equal "pair-sum-non-consecutive-list" #t (pair-sum? '(3 1 5 8) 6)) 
(test-assert "pair-sum-null-list-no-err" (not (pair-sum? '() 3))) 
(test-assert "pair-sum-single-list-ne" (not (pair-sum? '(5) 3)))
(test-assert "pair-sum-only-doubles-list-ne" (not (pair-sum? '(3 4) 6)) )
(test-assert "pair-sum-non-adjacent-list-ne" (not (pair-sum? '(1 5 8) 9)) )

;; Test pair-sum-lazy? edge cases
(test-equal "pair-sum-lazy-non-consecutive-list" #t (pair-sum-lazy? (make-lazy '(3 1 5 8)) 6)) 
(test-assert "pair-sum-lazy-single-list-ne" (not (pair-sum-lazy? one-lazy-item 3)))
(test-assert "pair-sum-lazy-only-doubles-list-ne" (not (pair-sum-lazy? one-lazy-item 6)) )
(test-assert "pair-sum-lazy-non-adjacent-list-ne" (not (pair-sum-lazy? (make-lazy '(1 5 8)) 9)) )

