(define seq
    (lambda (first last)
        (seq-h first last '())))

(define seq-h
    (lambda (first last lst)
        (if (> first last)
            lst
            (append (list first) (lambda () (seq (+ first 1) last))))))

(define inf-seq
    (lambda (first)
        (append (list first) (lambda () (inf-seq (+ first 1))))))

(define first-n
    (lambda (lazy-lst n)
        (first-n-h lazy-lst n '())))

(define first-n-h
    (lambda (lazy-lst n n-lst)
        (if (null? lazy-lst)
            n-lst
            (if (equal? n 0)
                n-lst
                (first-n-h ((cdr lazy-lst)) (- n 1) (append n-lst (list (car lazy-lst))))))))

(define nth
    (lambda (lazy-lst n)
        (if (null? lazy-lst)
            #f
            (if (equal? n 1)
                (car lazy-lst)
                (nth ((cdr lazy-lst)) (- n 1))))))

(define filter-multiples
    (lambda (lazy-lst n)
        (filter-multiples-h lazy-lst n '())))

(define filter-multiples-h
    (lambda (lazy-lst n new-lazy-lst)
        (if (null? lazy-lst)
            new-lazy-lst
            (if (integer? (/ (car lazy-lst) n))
                (filter-multiples-h ((cdr lazy-lst)) n new-lazy-lst)
                (append new-lazy-lst (list (car lazy-lst)) (lambda () (filter-multiples ((cdr lazy-lst)) n)))))))


(define check-prime
    (lambda (num)
        (check-prime-h num (- num 1)))) ; because of this 2 needs to always be the head of the list initially
(define check-prime-h
    (lambda (compra runner)
        (if (< runner 2)
            #t
            (if (integer? (/ compra runner))
                #f
                (check-prime-h compra (- runner 1))))))
(define find-prime
    (lambda (current)
        (if (check-prime (+ current 1))
            (+ current 1)
            (find-prime (+ current 1)))))
; these three functions is what helps me find a prime number

(define primes
    (lambda ()
        (primes-h 2))) ; I need a helper function because it must start at 2 and for it to be recurssive 

(define primes-h
    (lambda (cur)
        (append (list cur) (lambda () (primes-h (find-prime cur))))))