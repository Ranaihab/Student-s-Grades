# Student-s-Grades
Program to check whether the students passed or failed the exam. It is implemented using mpi.

You have a list of students' ids with their exam grade at a course written in a file. Some of them
will pass and some won’t pass. This depends on their grades if the grade was greater than or
equal 60 they will pass otherwise they will be asked to repeat the exam.

It is a parallel program implemented using mpi library and the tasks are:<br />
  Master process (rank 0)<br />
			- Read data from file<br />
			- Divide the students list by the number of processes you have then send it to them.<br />
    - Print the summation of the number of passed students received from each process.<br />
  For each process<br />
    - Receive part of students data<br />
    - Check if they passed or not and print message for each student<br />
      <Student ID> Passed The Exam<br />
      <Student ID> Failed. Please Repeat The Exam<br />
    - Calculate number of passed student then send it to master process (rank 0)

