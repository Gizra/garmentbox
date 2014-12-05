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
      .state('login', {
        url: '/',
        templateUrl: 'views/login.html',
        controller: 'LoginCtrl',
        onEnter: function($state, Auth,$timeout) {
          if (Auth.isAuthenticated()) {
            // We need to use $timeout to make sure $state is ready to
            // transition.
            $timeout(function() {
              $state.go('dashboard');
            });
          }
        }
      })
      .state('dashboard', {
        url: '/dashboard',
        templateUrl: 'views/dashboard/dashboard.html',
        controller: 'MainCtrl',
        onEnter: function($state, Auth, $timeout) {
          if (!Auth.isAuthenticated()) {
            $timeout(function() {
              $state.go('login');
            });
          }
        }
      })
      .state('dashboard.item', {
        url: '/item/:id',
        templateUrl: 'views/dashboard/dashboard.item.html',
        controller: 'MainCtrl'
      })
      .state('dashboard.item.variant', {
        url: '/:variant',
        templateUrl: 'views/dashboard/dashboard.item.variant.html',
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
