(define mult
  (lambda (a)
    (lambda (b)
      (* a b))))

(define curry3
    (lambda (fn)
        (lambda (x)
            (lambda (y)
                (lambda (z)
                    (fn x y z))))))

(define uncurry3
    (lambda (fn)
        (lambda (x y z)
            (((fn x) y) z))))

(define uncurry-h
    (lambda (fn lst tar)
        (if (= tar 1)
            (fn (car lst))
            (uncurry-h (fn (car lst)) (cdr lst) (- tar 1)))))

(define uncurry
    (lambda (fn)
        (lambda args
            (uncurry-h fn args (length args)))))
 
(define my-filter-h
    (lambda (fn og-lst new-lst)
        (if (null? og-lst)
            new-lst
            (if (fn (car og-lst))
                (my-filter-h fn (cdr og-lst) (append new-lst (list (car og-lst))))
                (my-filter-h fn (cdr og-lst) new-lst)))))

(define my-filter
    (lambda (fn og-lst)
        (my-filter-h fn og-lst '())))

(define union
    (lambda (a-lst b-lst)
        (if (null? b-lst)
            a-lst
            (if (member (car b-lst) a-lst)
                (union a-lst (cdr b-lst))
                (union (append a-lst (list (car b-lst))) (cdr b-lst))))))

(define intersect-h
    (lambda (a-lst b-lst new-lst)
        (if (null? a-lst)
            new-lst
            (if (member (car a-lst) b-lst)
                (intersect-h (cdr a-lst) b-lst (append new-lst (list (car a-lst))))
                (intersect-h (cdr a-lst) b-lst new-lst)))))

(define intersect
    (lambda (a-lst b-lst)
       (intersect-h a-lst b-lst '())))       

(define exists
    (lambda (fn lst)
        (if (> (length (my-filter fn lst)) 0)
            #t
            #f)))