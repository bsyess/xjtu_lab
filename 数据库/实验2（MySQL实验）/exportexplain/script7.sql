use employees;
EXPLAIN SELECT title, COUNT(DISTINCT emp_no)
FROM titles T
GROUP BY title
