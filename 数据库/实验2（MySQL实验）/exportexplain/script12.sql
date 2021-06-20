use employees;
EXPLAIN SELECT E.emp_no, CONCAT(first_name, ' ',last_name), from_date, to_date
FROM departments D, dept_emp DE, employees E
WHERE D.dept_no=DE.dept_no and E.emp_no=DE.emp_no and D.dept_name='Development'
