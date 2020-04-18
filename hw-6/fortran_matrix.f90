! Erick Juarez 
! CPSC 479 Sec 1
! HOMEWORK 6 - 4/20/20
! tested using GNU Fortran (GCC) 4.8.5
program fortran_matrix 
implicit none 

! Initialize 3 matrices with 4 rows & 4 columns 
integer, dimension(4, 4) :: A, B, C 
integer:: i, j

A = 4 ! set values of A to 4 
do i = 1, 4 ! set values of B(i,j) = i + j + 1
    do j = 1, 4
        B(i, j) = i + j + 1
    end do 
end do

C = A + B ! set values of C 

! Change values of 8 to 16 in C 
where(C == 8)
        C = 16
end where 

! print results 
do i = 1,4
    print '(a, i2, a, i2, 3i5)', 'A (row', i, '): ', A(i, :)
end do 

do i = 1,4
    print '(a, i2, a, i2, 3i5)', 'B (row', i, '): ', B(i, :)
end do 

do i = 1,4
    print '(a, i2, a, i2, 3i5)', 'C (row', i, '): ', C(i, :)
end do 


end