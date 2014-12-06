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

    /**
     * Redirect a logged in user to the dashboard.
     *
     * @param $state
     *   The ui-router state.
     * @param Auth
     *   The Auth service.
     * @param $timeout
     *   The timeout service.
     */
    var redirectToDashbaord = function($state, Auth,$timeout) {
      if (Auth.isAuthenticated()) {
        // We need to use $timeout to make sure $state is ready to
        // transition.
        $timeout(function() {
          $state.go('dashboard');
        });
      }
    };

    /**
     * Redirect a user to a 403 error page.
     *
     * @param $state
     *   The ui-router state.
     * @param Auth
     *   The Auth service.
     * @param $timeout
     *   The timeout service.
     */
    var page403 = function($state, Auth,$timeout) {
      if (!Auth.isAuthenticated()) {
        // We need to use $timeout to make sure $state is ready to
        // transition.
        $timeout(function() {
          $state.go('403');
        });
      }
    };

    // Now set up the states.
    $stateProvider
      .state('login', {
        url: '/login',
        templateUrl: 'views/login.html',
        controller: 'LoginCtrl',
        onEnter: redirectToDashbaord
      })
      .state('dashboard', {
        url: '',
        templateUrl: 'views/dashboard/main.html',
        controller: 'DashboardCtrl',
        onEnter: page403
      })
      .state('dashboard.items', {
        url: '/items',
        templateUrl: 'views/dashboard/items/items.html',
        controller: 'ItemsCtrl',
        onEnter: page403
      })
      .state('dashboard.items.variants', {
        url: '/:id',
        templateUrl: 'views/dashboard/items/item.variants.html',
        controller: 'ItemsCtrl',
        onEnter: page403
      })
      .state('dashboard.items.variants.variant', {
        url: '/:variant',
        templateUrl: 'views/dashboard/items/item.variant.html',
        controller: 'ItemsCtrl',
        onEnter: page403
      })
      .state('dashboard.companies', {
        url: '/companies',
        templateUrl: 'views/dashboard/companies/companies.html',
        controller: 'CompaniesCtrl',
        onEnter: page403
      })
      .state('dashboard.companies.company', {
        url: '/:id',
        templateUrl: 'views/dashboard/companies/companies.company.html',
        controller: 'CompaniesCtrl',
        onEnter: page403
      })
      .state('403', {
        url: '/403',
        templateUrl: 'views/403.html'
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
