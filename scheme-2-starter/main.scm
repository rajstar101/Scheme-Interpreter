(define sum
    (lambda (lst)
        (if (null? lst)
            0
            (+ (car lst) (sum (cdr lst))))))
                
(define length
    (lambda (lst)
        (if (null? lst)
            0
            (+ 1 (length (cdr lst))))))

(define keep-first-n
    (lambda (n lst)
        (if (< n 0)
            '()
            (if (> n (length lst))
                '()
                (if (equal? n 0)
                    '()
                    (if (equal? n 1)
                        (list (car lst))
                        (if (equal? n 2)
                            (list (car lst) (car (cdr lst)))
                            (cons (car lst) (keep-first-n (- n 1) (cdr lst))))))))))


(define mystery
    (lambda (lst target)
        (if (or (< target 0) (null? lst))
            #f
            (if (= target 0)
                #t
                (or (mystery lst (- target (car lst)))
                    (mystery (cdr lst) target))))))



(define z (mystery '(9 5 3) 7))
z