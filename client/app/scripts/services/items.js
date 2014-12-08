'use strict';

/**
 * @ngdoc service
 * @name clientApp.items
 * @description
 * # items
 * Service in the clientApp.
 */
angular.module('clientApp')
  .service('Items', function ($q, $http, $timeout, Config, $rootScope, $log) {

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
     * Create a new item.
     *
     * @param data
     *   Object with data to be saved.
     */
    this.create= function(data) {
      var deferred = $q.defer();
      var url = Config.backend + '/api/items';

      $http({
        method: 'POST',
        url: url,
        data: data
      }).success(function(response) {
        // We don't need to query the backend again - we can simply append the
        // new items to the cached list.
        data = cache ? cache.data : [];
        data.unshift(response.data[0]);
        setCache(data);

        deferred.resolve(response.data[0]);
      });

      return deferred.promise;
    };

    /**
     * Return items array from the server.
     *
     * @returns {$q.promise}
     */
    function getDataFromBackend() {
      var deferred = $q.defer();
      var url = Config.backend + '/api/items';

      $http({
        method: 'GET',
        url: url,
        params: {sort: '-id'}
      }).success(function(response) {
        setCache(response.data);
        deferred.resolve(response.data);
      });

      return deferred.promise;
    };

    /**
     * Save meters in cache, and broadcast en event to inform that the meters data changed.
     *
     * @param meters
     */
    var setCache = function(data) {
      // Cache meters data.
      cache = {
        data: data,
        timestamp: new Date()
      };

      // Clear cache in 60 seconds.
      $timeout(function() {
        cache.data = undefined;
      }, 60000);

      // Broadcast a change event.
      $rootScope.$broadcast('gb.items.changed');
    }

  });
