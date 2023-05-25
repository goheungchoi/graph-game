import React from 'react';
import ReactDOM from 'react-dom/client';
import './style/index.css';
import App from './App';
import ErrorPage from './routes/ErrorPage';
import Home from './routes/Home'
import reportWebVitals from './reportWebVitals';

import { Provider } from 'react-redux';
import store from './redux/store.js';
import { 
  createBrowserRouter,
  RouterProvider 
} from 'react-router-dom';

const router = createBrowserRouter([
  {
    path: "/",
    element: <Home />
  }
])

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  <Provider store={store}>
    <RouterProvider router={router} />
  </Provider>
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
