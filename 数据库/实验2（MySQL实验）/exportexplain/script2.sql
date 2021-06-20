use employees;
EXPLAIN SELECT D.dept_no, D.dept_name, from_date, to_date, E.emp_no, CONCAT(first_name, ' ',last_name)
FROM departments D, employees E, dept_manager DM
WHERE D.dept_no=DM.dept_no and E.emp_no=DM.emp_no
GROUP BY D.dept_no, from_date, to_date
ORDER BY D.dept_no, from_date
