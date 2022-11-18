(define make-account
    (lambda ()
        (let ((balance 0))
            (lambda (amt)
                    (set! balance (- balance amt))
                    balance))))
