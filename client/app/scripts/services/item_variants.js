'use strict';

/**
 * @ngdoc service
 * @name clientApp.itemVariants
 * @description
 * # itemVariants
 * Service in the clientApp.
 */
angular.module('clientApp')
  .service('ItemVariants', function ($q, $http, $timeout, Config, $rootScope, $log) {

    // A private cache key.
    var cache = {};

    /**
     * Return the promise with the items list, from cache or the server.
     *
     * @returns {*}
     */
    this.get = function(itemId) {
      if (cache[itemId]) {
        return $q.when(cache[itemId].data);
      }

      return getDataFromBackend(itemId);
    };

    /**
     * Return items array from the server.
     *
     * @returns {$q.promise}
     */
    function getDataFromBackend(itemId) {
      $log.log('item variant from backend');
      var deferred = $q.defer();
      var url = Config.backend + '/api/item_variants';
      var params = !!itemId ? {item: itemId} : {};

      $http({
        method: 'GET',
        url: url,
        params: params
      }).success(function(response) {
        setCache(itemId, response.data);
        deferred.resolve(response.data);
      });

      return deferred.promise;
    }

    /**
     * Save meters in cache, and broadcast en event to inform that the meters data changed.
     *
     * @param itemId
     *   The item ID.
     * @param data
     *   The data to cache.
     */
    var setCache = function(itemId, data) {
      // Cache data.
      cache[itemId] = {
        data: data,
        timestamp: new Date()
      };

      // Clear cache in 60 seconds.
      $timeout(function() {
        delete(cache[itemId]);
      }, 60000);

      // Broadcast a change event.
      $rootScope.$broadcast('gb.item_variants.changed');
    }

  });
