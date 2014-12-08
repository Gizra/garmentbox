'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:ItemsAddCtrl
 * @description
 * # ItemsAddCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('ItemsAddCtrl', function ($scope, Items) {

    $scope.data = {};

    /**
     * Create a new item.
     *
     * @param data
     *   Object with data to be saved.
     */
    $scope.create = function(data) {
      Items.create(data);
    }
  });
