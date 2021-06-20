use employees;
EXPLAIN SELECT E.emp_no, CONCAT(first_name, ' ',last_name), from_date, to_date, dept_name
FROM employees E, dept_emp DE, departments D
WHERE E.emp_no=DE.emp_no and D.dept_no=DE.dept_no
ORDER BY E.emp_no, from_date
