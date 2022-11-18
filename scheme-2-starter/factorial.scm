(define factorial
  (lambda (n)
    (if (equal? n 1)
        1
        (* n (factorial (- n 1))))))

,tr (factorial 5)
