'use strict';

/**
 * @ngdoc service
 * @name clientApp.companies
 * @description
 * # companies
 * Service in the clientApp.
 */
angular.module('clientApp')
  .service('Companies', function ($q, $http, $timeout, Config, $rootScope, localStorageService) {

    // A private cache key.
    var cache = {};

    /**
     * Return the promise with the items list, from cache or the server.
     *
     * @returns {*}
     */
    this.get = function() {
      return $q.when(cache.data || getDataFromBackend());
    };

    /**
     * Set the active company.
     *
     * A user may have multiple companies, but for some queries we may want to
     * set the "active" one.
     *
     * @param int id
     *   The ID of the company.
     */
    this.setActive = function(id) {
      localStorageService.set('active_company', id);
    };

    /**
     * Return the active company.
     *
     * @returns int
     *   The ID of the active company if set.
     */
    this.getActive = function() {
      return localStorageService.get('active_company');
    };

    /**
     * Return items array from the server.
     *
     * @returns {$q.promise}
     */
    var getDataFromBackend = function() {
      var deferred = $q.defer();
      var url = Config.backend + '/api/companies';

      $http({
        method: 'GET',
        url: url
      }).success(function(response) {
        setCache(response.data);
        deferred.resolve(response.data);
      });

      return deferred.promise;
    };

    /**
     * Set the cache from the server.
     *
     * @param data
     *   The data to cache
     */
    var setCache = function(data) {
      // Cache data.
      cache = {
        data: data,
        timestamp: new Date()
      };

      // Clear cache in 60 seconds.
      $timeout(function() {
        cache.data = undefined;
      }, 60000);

      // Broadcast a change event.
      $rootScope.$broadcast('gb.companies.changed');
    }

  });
