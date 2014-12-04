'use strict';

/**
 * @ngdoc overview
 * @name clientApp
 * @description
 * # clientApp
 *
 * Main module of the application.
 */
angular
  .module('clientApp', [
    'ngAnimate',
    'ngCookies',
    'ngSanitize',

    'config',
    'LocalStorageModule',
    'ui.router'
  ])
  .config(function($stateProvider, $urlRouterProvider, $httpProvider) {

    // Now set up the states.
    $stateProvider
      .state('dashboard', {
        url: '/',
        templateUrl: 'views/dashboard.html',
        controller: 'MainCtrl'
      })
      .state('dashboard.login', {
        url: 'login',
        templateUrl: 'views/dashboard.login.html',
        controller: 'MainCtrl'
      })
      .state('dashboard.main', {
        url: 'dashboard',
        templateUrl: 'views/dashboard.main.html',
        controller: 'MainCtrl'
      });

    // For any unmatched url, redirect to '/'.
    $urlRouterProvider.otherwise('/');

    // Define interceptors.
    $httpProvider.interceptors.push(function ($q, Auth, localStorageService) {
      return {
        'request': function (config) {
          if (!config.url.match(/login-token/)) {
            config.headers = {
              'access_token': localStorageService.get('access_token')
            };
          }
          return config;
        },

        'response': function(result) {
          if (result.data.access_token) {
            localStorageService.set('access_token', result.data.access_token);
          }
          return result;
        },

        'responseError': function (response) {
          if (response.status === 401) {
            Auth.authFailed();
          }

          return $q.reject(response);
        }
      };
    });
  });
