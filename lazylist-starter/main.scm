(define gen-list
    (lambda (x y)
        (if (> x y)
            '()
            (append (list x) (gen-list (+ x 1) y)))))


(define pair-sum?-h
    (lambda (lstx lsty goal)
        (if (null? lstx)
            #f
            (if (null? lsty)
                (pair-sum?-h (cdr lstx) (cdr lstx) goal)
                (if (equal? lstx lsty)
                    (pair-sum?-h lstx (cdr lsty) goal)
                    (if (= (+ (car lstx) (car lsty)) goal)
                        #t
                        (pair-sum?-h lstx (cdr lsty) goal)))))))

(define pair-sum?
    (lambda (lst val)
        (pair-sum?-h lst lst val)))

(define gen-lazy-list
  (lambda (start stop)
    (if (> start stop)
        #f
        (cons start
            (lambda () (gen-lazy-list (+ start 1) stop))))))

(define pair-sum-lazy?-h
    (lambda (lstx lsty goal)
        (if (equal? (cdr lstx) #f)
            #f
            (if (equal? (cdr lsty) #f)
                (pair-sum-lazy?-h ((cdr lstx)) ((cdr lstx)) goal)
                (if (equal? lstx lsty)
                    (pair-sum-lazy?-h lstx ((cdr lsty)) goal)
                    (if (= (+ (car lstx) (car lsty)) goal)
                        #t
                        (pair-sum-lazy?-h lstx ((cdr lsty)) goal)))))))

(define pair-sum-lazy?
    (lambda (lst val)
        (pair-sum-lazy?-h lst lst val)))

(define make-lazy?-h
    (lambda (lst elst)
        (if (equal ))))

(define make-lazy?
    (lambda (lst)
        (cons (car lst)
        (lambda () (gen-lazy-list (cdr lst) (make-lazy? (cdr lst)))))))

(make-lazy '(1 5))