(define entry
    (lambda (bst)
        (if (null? bst)
            #f
            (if (integer? (car bst))
                (car bst)
                #f))))

(define left
    (lambda (bst)
        (if (null? bst)
            #f
            (if (list? (car (cdr bst)))
                (car (cdr bst))
                #f))))

(define right
    (lambda (bst)
        (if (null? bst)
            #f
            (if (list? (car (cdr (cdr bst))))
                (car (cdr (cdr bst)))
                #f))))

(define is-bst
    (lambda (bst)
        (if (not (list? bst))
            #f
            (if (null? bst)
                #t
                (if (not (integer? (entry bst)))
                    #f
                    (if (null? (cdr bst))
                        #f
                        (if (equal? (left bst) #f)
                            #f
                            (if (null? (cdr (cdr bst)))
                                #f
                                (if (equal? (right bst) #f)
                                #f
                                #t)))))))))

(define make-bst
    (lambda (elt left-bst right-bst)
        (if (not (integer? elt))
            #f
            (if (equal? (is-bst left-bst) #f)
                #f
                (if (equal? (is-bst right-bst) #f)
                    #f
                    (append (list elt left-bst) (list right-bst)))))))


(define preorder
    (lambda (bst)
        (if (list? bst)
            (if (null? bst)
                '()
                (append (list (car bst)) (preorder (car (cdr bst))) (preorder (car (cdr (cdr bst))))))
            (list bst))))

(define inorder
    (lambda (bst)
        (if (list? bst)
            (if (null? bst)
                '()
                (append (inorder (car (cdr bst))) (list (car bst)) (inorder (car (cdr (cdr bst))))))
            (list bst))))

(define postorder
    (lambda (bst)
        (if (list? bst)
            (if (null? bst)
                '()
                (append (postorder (car (cdr bst))) (postorder (car (cdr (cdr bst)))) (list (car bst))))
            (list bst))))

(define insert
    (lambda (v bst)
        (if (null? bst)
            (make-bst v '() '())
            (if (= v (entry bst))
                bst
                (if (> v (entry bst))
                    (make-bst (entry bst) (left bst) (insert v (right bst)))
                    (make-bst (entry bst) (insert v (left bst)) (right bst)))))))

;,tr (make-bst 1 '() '(3))
