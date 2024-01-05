var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
var axios = require('axios');
var cors = require('cors');
var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');

var app = express();

// view engine setup
app.use(cors());
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);

app.post('/register', async (req, res, next) => {
  try {
    const { email, username, password } = req.body;
    const response = await axios.post('http://beastgres:8000/api/db', {
      method: 'register',
      email: email,
      username: username,
      password: password
    });

    // Check response and render success or error view
    if (response.data === 'Registration successful') {
      // Render a success page or send a success response
      res.render('register-success', { title: 'Registration Success' });
    } else {
      // Render an error page or send an error response
      res.render('register-fail', { title: 'Registration Failed', error: response.data });
    }
  } catch (error) {
    // Handle network or other errors
    next(error);
  }
});


// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
