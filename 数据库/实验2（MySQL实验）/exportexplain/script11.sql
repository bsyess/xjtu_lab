use employees;
EXPLAIN SELECT D.dept_no, dept_name, CONCAT(first_name, ' ',last_name)
FROM departments D, dept_manager DM, employees E
WHERE D.dept_no=DM.dept_no and E.emp_no=DM.emp_no
ORDER BY D.dept_no, from_date

